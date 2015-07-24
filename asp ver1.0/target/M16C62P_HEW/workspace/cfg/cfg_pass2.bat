copy %2\cfg1_out.srec .
%1\target\M16C62P_HEW\gensyms.exe %2\cfg.map
%1\cfg\cfg.exe --pass=2 --kernel=asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\m16c_nc30\prc_def.csv -I%1 -I%1\arch -I..\..\include -I%1\kernel -I%1\target\M16C62P_HEW -T %1\target\M16C62P_HEW\target.tf %1\Apli\job.cfg
copy kernel_cfg.c ..\job
copy kernel_cfg.h ..\job
copy kernel_cfg_asm.a30 ..\job