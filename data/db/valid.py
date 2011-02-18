# -*- coding: utf-8 -*-

from lxml import etree

# on charge le fichier validateur
f = open("db.xsd","r")
xmlschema_doc = etree.parse(f)
schema = etree.XMLSchema(xmlschema_doc)

# on charge le fichier a validé
x = open("db.xml","r")
config = etree.parse(x)

# on valide :-)
print "renvoie True si param.xml est conforme : " + str(schema.validate(config))
print "message d'erreur -> " + str(schema.assertValid(config))
