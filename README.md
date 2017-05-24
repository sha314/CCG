# CCG
Character Combination Generator (CCG)

It is a command-line program, written in C++ language, that generates combination of characters from a given character set with the asked width. This program should be compiled with cmake 3.6 or higher.

How to use CCG program:
  Compilation:
  for linux user
  
    cmake . && make
      
  Run from command-line:
    for linux user
    
      ./bin/ccg -h
      ./bin/ccg -w 3 -c "(a-z),[65-90]" -f dummy1 -s
      ./bin/ccg -w 3 -c "(a-z),[65-90],!@#$" -f dummy -s -t
      ./bin/ccg -w 3 -c "(a-z),[65-90],!@#$\," -f dummy -s -t

    
  Note:
    Widows user should user '\\' instead of '/'.
  
  Help:
    read the manual/rccg_manual.txt
