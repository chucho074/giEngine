@echo off
call "%USERPROFILE%/anaconda3/Scripts/activate.bat" activate dmodel
cd /d "G:/Dev/nvdiffmodeling"
cmd /c "python train.py --config configs/spot.json"