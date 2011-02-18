(TeX-add-style-hook "report_perso"
 (lambda ()
    (LaTeX-add-labels
     "img_#1"
     "img_#4"
     "img_#1_#4")
    (TeX-add-symbols
     '("imageext" 3)
     '("subimage" 7)
     '("image" 3)
     "cit"
     "gras"
     "NQ"
     "clap"
     "ligne"
     "haut"
     "bas"
     "maketitle"
     "date"
     "author"
     "title"
     "blurb"
     "location")
    (TeX-run-style-hooks
     "color"
     "csquotes"
     "xcolor"
     "algorithm2e"
     "lined"
     "boxed"
     "commentsnumbered"
     "hyperref"
     "url"
     "caption"
     "subfig"
     "listings"
     "pdfpages"
     "appendix"
     "tocbibind"
     "nottoc"
     "notlof"
     "notlot"
     "float"
     "setspace"
     "lastpage"
     "geometry"
     "graphicx"
     "pdftex"
     "cite"
     "fancyhdr"
     "babel"
     "frenchb"
     "fontenc"
     "T1"
     "inputenc"
     "utf8")))

