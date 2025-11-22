@echo off
echo ===========================
echo   Building
echo ===========================
if exist build (
    cd build

    echo ===========================
    echo   RUNNING CMAKE CONFIGURE
    echo ===========================
    cmake ..

    echo ===========================
    echo   BUILDING PROJECT
    echo ===========================
    cmake --build .

    echo ===========================
    echo   DONE! 
    echo ===========================

    echo ===========================
    echo   Running.... 
    echo ===========================

    cd ..
    cd compiled
    if exist Debug (
        cd Debug
        ViraChrono.exe
    )
    if exist Release (
        cd Release
        ViraChrono.exe
    )


)
