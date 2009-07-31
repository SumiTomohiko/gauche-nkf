;;;
;;; Test nkf
;;;

(use gauche.test)

(test-start "nkf")
(use nkf)
(test-module 'nkf)

(test* "Convert ASCII to ASCII" "foo" (nkf '("-w") "foo"))
(test* "Convert EUC-JP to UTF-8" "あ" (nkf '("-w") #*"\xa4\xa2"))
(test* "Convert Shift-JIS to UTF-8" "あ" (nkf '("-w") #*"\x82\xa0"))

;; epilogue
(test-end)

;; vim: tabstop=2 shiftwidth=2 expandtab softtabstop=2 filetype=scheme
