@echo off
openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program Project.hex verify reset exit"
pause