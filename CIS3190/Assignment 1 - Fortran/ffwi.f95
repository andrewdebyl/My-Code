!   Program no.: f-4
!   Fortran iv program to calculate canadian forest
!   fire weather index for a dec pdp 11 at p.f.e.s.
!   reads data and prints out in metric units.
!
program Fire
    implicit none
!   Declaring all variables to be used
    real :: preFFMC, preDMC, preDC, temp, afterR, tx, humd, wind, &
    & FFMCaft, rainFunc, intX, logDry, emcWet, correct, &
    & emcDry, amnt, startM, finalMC, ffm, dryF, logFWI, si, ffmF, &
    & intFWI, cc, ratioF, wmi, rainEff, dmc, dryingF, todayFFM, &
    & dcAftRain, bui, smi, dc, fwi, dmcAftR, wmr, rw, rain
    integer :: ndays, idays, j, l, i, nn, m, ih, iw, iffm, &
    & idmc,idc,isi,ibui,ifwi
    character (len=20) :: fname
    logical :: bool

    real, dimension(12) :: dayL, dayLDC
    integer, dimension(12) :: lmon

!   Formatting the output of the file
    write(*,104)
104 format(2X,'Program no.: f-4')
101 format(F4.1,I4,I4,F4.1)

!
!   Reads initial input
!
    call getInitialInput (fname, bool, j, lmon, dayL, dayLDC, &
    & preFFMC, preDMC, preDC, m, ndays)
!

    do j = m, 12
        nn = lmon(j)
103     format(1X,'  DATE  TEMP  RH   WIND  RAIN   FFMC   DMC   DC &
        &  ISI   BUI   FWI'/)

        if(j == m) then
            idays = lmon(j) - ndays + 1
        else
            idays = 1
        end if   
!
!   Reads daily weather data
!
        l = 0
        do i = idays,nn
            l = l + 1
            read(1, 101, end = 201) temp, ih, iw, afterR
      
            if(l == 1) then
                write(*, 103)
            end if

            tx = temp
            humd = ih
            wind = iw
            rain = afterR
!
!   Fine fuel moisture code
!
            call fuelCode (afterR, FFMCaft, preFFMC, amnt,rainFunc, &
            & correct, startM,emcDry,humd,emcWet,temp,finalMC,intX, &
            & wind,logDry,ffm)
!
!   Duff moisture code
!
            call moistureCode (temp, dryF, humd,dayL,j,afterR,amnt, &
            & rw,wmi, preDMC,rainEff,wmr,dmcAftR,dmc)
!
!   Drought code
!
            call droughtCode (temp, dryingF, dayLDC, j, afterR, &
            & dcAftRain, preDC, dc, amnt, rw, smi)
!
!   Initial spread index, buildup index, fire weather index
!
            call sbwIndex (todayFFM,ffm,ffmF,si,wind,bui,dc,dmc,&
            & ratioF,cc, intFWI,fwi,logFWI)
!   
!   Output
!
            call getOutput(idc, iffm, idmc, isi, ibui, ifwi, j, & 
            & i, tx, ih, iw, rain, preFFMC, ffm, preDMC, dmc, preDC, &
            & dc, si, bui, fwi)

        end do

        write(*,*)''
    end do

201 stop

end program Fire

!
!--------------------I/O SUBPROGRAMS----------------------!
!
!   Initial Input
!
subroutine getInitialInput (fname, bool, j, lmon, dayL, dayLDC, &
    & preFFMC, preDMC, preDC, m, ndays)

    real, intent (inout)  :: preFFMC, preDMC, preDC
    integer, intent (inout) :: j, m, ndays
    character(len=20), intent (inout) :: fname
    logical, intent (inout) :: bool
    real, dimension(12), intent (inout) :: dayL, dayLDC
    integer, dimension(12), intent (inout) :: lmon

!   Reading the file name
    write (*,*) 'Enter the input filename: '
    read (*,'(A)') fname

!   Checking if the file exists
    inquire(file=fname, exist=bool)
    if (.not. bool) then
        write (*,*) 'File does not exist - abort'
        call exit(0)  
    else
        open(1, file = fname, status='old')
    end if

!   Formatting the output of the file
100 format(I2,F4.1,F4.1)
102 format(F4.1,F4.1,F5.1,I2,I2)

!   Reads length of months, and day length factors
    do j = 1, 12
        read(1,100) lmon(j), dayL(j), dayLDC(j)
    end do

!   Reads initial values of ffmc, dmc, dc, starting month and number
!   of days of data starting month.
    read(1,102) preFFMC,preDMC,preDC,m,ndays
end subroutine getInitialInput

!
!   Output
!
subroutine getOutput (idc, iffm, idmc, isi, ibui, ifwi, j, i, tx, &
    & ih, iw, rain, preFFMC, ffm, preDMC, dmc, preDC, dc,si,bui,fwi)

    real, intent (inout)  :: tx, rain, preFFMC, ffm, preDMC, dmc, &
    & preDC, dc, si, bui, fwi
    integer, intent (inout) :: idc,iffm,idmc,isi,ibui,ifwi,j,i,ih,iw

    idc=int(dc+0.5)
    iffm=int(ffm+0.5)
    idmc=int(dmc+0.5)
    isi=int(si+0.5)
    ibui=int(bui+0.5)
    ifwi=int(fwi+0.5)

!   Displaying the outputed data
    write(*,106) j,i,tx,ih,iw,rain,iffm,idmc,idc,isi,ibui,ifwi
106 format(1x,2i3,f6.1,i4,i6,f7.1,6i6)

    preFFMC=ffm
    preDMC=dmc
    preDC=dc
end subroutine getOutput