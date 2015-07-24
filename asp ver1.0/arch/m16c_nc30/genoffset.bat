echo %1

%1\m16coffset.exe -R:%2\makeoffset.a30 -O:%2\offset.inc
copy %2\offset.inc %3
