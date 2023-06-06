@echo off
call "%USERPROFILE%/anaconda3/Scripts/activate.bat" activate dmodel
cd /d "G:/Dev/nvdiffmodeling"
cmd /c "python giAMR.py --config G:/Dev/giEngine/bin/Resources/giAMR/giAMR.json"