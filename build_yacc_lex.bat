C:\chenyu\Software\GnuWin32\bin\flex -olex.yy.cpp .\verilog.l
del verilog.tab.*
copy .\verilog.y C:\chenyu\Software\GnuWin32\bin\
cd C:\chenyu\Software\GnuWin32\bin\
bison -vd -o verilog.tab.cpp verilog.y
copy verilog.tab.* C:\ChenYu\work\yacclex\
pause