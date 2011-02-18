(TeX-add-style-hook "main"
 (lambda ()
    (LaTeX-add-bibliographies
     "bibli/biblio")
    (LaTeX-add-labels
     "sec:bibli")
    (TeX-run-style-hooks
     "report_perso"
     "latex2e"
     "rep12"
     "report"
     "a4paper"
     "12pt"
     "chap/abstract"
     "chap/introduction"
     "chap/analyse"
     "chap/conception"
     "chap/realisation"
     "chap/resultats"
     "chap/conclusion"
     "chap/annexes")))

