/*
 * synchttp.h
 *
 * Copyright (c) 2010-2011 see AUTHORS
 */

/*
 * This file is part of nuqleosim.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef HEADER_SYNCHTTP
#define HEADER_SYNCHTTP

#include <QHttp>
#include <QEventLoop>
#include <QBuffer>
#include <QDebug>

class SyncHTTP: public QHttp
{
	Q_OBJECT
	public:
    /// structors
    SyncHTTP( QObject * parent = 0 )
		:QHttp(parent),requestID(-1),status(false){}

    SyncHTTP( const QString & hostName, quint16 port = 80,
              QObject * parent = 0 )
		:QHttp(hostName,port,parent),requestID(-1),status(false){}

    virtual ~SyncHTTP(){}

    /// send GET request and wait until finished
    bool syncGet ( const QString & path, QIODevice * to = 0 )
		{
			///connect the requestFinished signal to our finished slot
			connect(this,SIGNAL(requestFinished(int,bool)),
                    SLOT(finished(int,bool)));
			/// start the request and store the requestID
			requestID = get(path, to);
			/// block until the request is finished
			loop.exec();
			/// return the request status
			return status;
		}

    /// send POST request and wait until finished
    bool syncPost ( const QString & path, QIODevice * data,
                    QIODevice * to = 0 )
		{
			///connect the requestFinished signal to our finished slot
			connect(this,SIGNAL(requestFinished(int,bool)),
                    SLOT(finished(int,bool)));
			/// start the request and store the requestID
			requestID = post(path, data , to );
			/// block until the request is finished
			loop.exec();
			/// return the request status
			return status;
		}

    bool syncPost ( const QString & path, const QByteArray& data,
                    QIODevice * to = 0 )
		{
			/// create io device from QByteArray
			QBuffer buffer;
			buffer.setData(data);
			return syncPost(path,&buffer,to);
		}

protected slots:
    virtual void finished(int idx, bool err)
		{
			/// check to see if it's the request we made
			if(idx!=requestID)
				return;
			/// set status of the request
			status = !err;
			/// end the loop
			loop.exit();
		}

private:
    /// id of current request
    int requestID;
    /// error status of current request
    bool status;
    /// event loop used to block until request finished
    QEventLoop loop;
};

#endif
