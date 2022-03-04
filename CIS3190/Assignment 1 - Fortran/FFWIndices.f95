!-------------------------SUBROUTINES--------------------------------!
!
!   In this file, it contains all ths subroutines to preform the 
!   calculations of the values needed, which are: fine fuel moisture 
!   code, duff moisture code, drought code, Initial spread index, 
!   buildup index, and fire weather index.
!   The ffwi.f95 program calls these subroutines.

!
!   Fine fuel moisture code
!
subroutine fuelCode (afterR,FFMCaft,preFFMC,amnt,rainFunc,correct,&
      & startM,emcDry,humd,emcWet,temp,wm,intX,wind,logDry,ffm)
      
      real, intent (inout)  :: afterR,FFMCaft,preFFMC,amnt,rainFunc,&
      &correct,startM,emcDry,humd,emcWet,temp,wm,intX,wind,logDry,ffm
  
      if(afterR <= 0.5) then 
          afterR = 0.0
          FFMCaft = preFFMC
      else
          amnt = afterR
          if(amnt <= 1.45) then
              rainFunc = 123.85 - (55.6 * alog(amnt + 1.016))
          else
              if(amnt - 5.75 <= 0) then
                  rainFunc = 57.87 - (18.2 * alog(amnt - 1.016))
              else
                  rainFunc = 40.69 - (8.25 * alog(amnt - 1.905))
              end if
          end if
  
          correct = 8.73 * exp(-0.1117 * preFFMC)
          FFMCaft = (preFFMC/100.) * rainFunc + (1.0 - correct)
  
          if(FFMCaft < 0.) then
            FFMCaft = 0.0
          end if
      end if
  
      startM = 101. - FFMCaft
  
      emcDry=0.942*(humd**0.679)+(11.*exp((humd-100.)/10.))+0.18* &
      & (21.1-temp)*(1.-1./exp(0.115*humd))
  
      if(startM-emcDry < 0) then
          emcWet=0.618*(humd**0.753)+(10.*exp((humd-100.)/10.))+0.18*&
          & (21.1-temp)*(1.-1./exp(0.115*humd))
  
          if(startM < emcWet) then
              wm=emcWet-(emcWet-startM)/1.9953
          end if
      else if (startM-emcDry == 0) then
          wm=startM
      else
          intX=0.424*(1.-(humd/100.)**1.7)+(0.0694*(wind**0.5))* &
          & (1.-(humd/100.)**8)
          logDry=intX*(0.463*(exp(0.0365*temp)))
          wm=emcDry+(startM-emcDry)/10.**logDry
      end if
  
      ffm = 101. - wm
  
      if(ffm > 101.) then
          ffm = 101.
      else
          if(ffm < 0) then
              ffm = 0.0
          end if
      end if
  
  end subroutine fuelCode
  
  !
  !   Duff moisture code
  !
  subroutine moistureCode (temp, dryF, humd,dayL,j,afterR,amnt,rw, &
      & wmi,preDMC,rainEff,wmr,dmcAftR,dmc)

      integer, intent (inout)  :: j
      real, intent (inout)  :: temp,dryF,humd,afterR,amnt,rw,wmi, &
      & preDMC,rainEff,wmr,dmcAftR,dmc
      real, dimension(12), intent (inout) :: dayL
  
      if(temp + 1.1 < 0.) then
          temp = -1.1
      end if
  
      dryF = 1.894 * (temp + 1.1) * (100. - humd) * (dayL(j)*0.0001)
  
      if(afterR > 1.5) then    
          amnt = afterR
          rw = 0.92 * amnt - 1.27
          wmi = 20.0 + 280. / exp(0.023 * preDMC)
  
              if(preDMC <= 33.) then
                  rainEff = 100. / (0.5 + 0.3 * preDMC)
              else
                  if(preDMC - 65. <= 0) then      
                      rainEff = 14. - 1.3 * alog(preDMC)
                  else
                      rainEff = 6.2 * alog(preDMC) - 17.2
                  end if
              end if
  
          wmr = wmi + (1000. * rw) / (48.77 + rainEff * rw)
          dmcAftR=43.43 * (5.6348 - alog(wmr - 20.))
      else
          dmcAftR = preDMC
      end if
  
      if(dmcAftR < 0.) then
          dmcAftR = 0.0
      end if
      dmc = dmcAftR + dryF
  
  end subroutine moistureCode
  
  !
  !   Drought Code
  !
  subroutine droughtCode (temp,dryingF,dayLDC,j,afterR,dcAftRain, &
      & preDC, dc, amnt, rw, smi)

      integer, intent (inout)  :: j
      real, intent (inout)  :: temp, dryingF, afterR, dcAftRain, &
      & preDC, dc, amnt, rw, smi
      real, dimension(12), intent (inout) :: dayLDC
  
      if (temp + 2.8 >= 0.) then
          dryingF = (.36 * (temp + 2.8) + dayLDC(j)) / 2.
      else
          temp = -2.8
      end if
  
      if(afterR <= 2.8) then
          dcAftRain = preDC
          dc = dcAftRain + dryingF
      else
          amnt = afterR
          rw = 0.83 * amnt - 1.27
          smi = 800. * exp(-preDC / 400.)
          dcAftRain = preDC - 400. * alog(1. + ((3.937 * rw)/smi))
        
          if(dcAftRain > 0.) then
              dc = dcAftRain + dryingF
          else
              dcAftRain = 0.0
              dc = dcAftRain + dryingF
          end if
      end if
  
      if(dc < 0.) then
          dc = 0.0
      end if
  
  end subroutine droughtCode
  
  !
  !   Initial spread index, buildup index, fire weather index
  !
  subroutine sbwIndex (todayFFM, ffm,ffmF, si, w,bui,dc,dmc,ratioF, &
      & cc,intFWI,fwi,logFWI)

      real, intent (inout)  :: todayFFM, ffm,ffmF,si,w,bui,dc,dmc, &
      & ratioF,cc,intFWI,fwi,logFWI
  
      todayFFM = 101. - ffm
      ffmF = 19.1152 * exp((-0.1386) * todayFFM) * (1. + todayFFM** &
      & 4.65/7950000.)

      si = ffmF * exp(0.05039 * w)
      bui = (0.8 * dc * dmc) / (dmc + 0.4 * dc)
  
      if(bui < dmc) then
          ratioF = (dmc - bui) / dmc
          cc = 0.92 + (0.0114 * dmc)**1.7
          bui = dmc - (cc * ratioF)
          if(bui < 0.) then
              bui = 0.
          end if
      end if
  
      if(bui > 80.) then
          intFWI = 0.1*si*(1000. / (25. + 108.64 / exp(0.023 * bui)))
      else
          intFWI = 0.1 * si * (0.626 * bui**0.809 + 2.)
      end if
      
      if(intFWI - 1.0 <= 0.) then 
          fwi = intFWI
      else
          logFWI = 2.72 * (0.43 * alog(intFWI))**0.647
          fwi = exp(logFWI)
      end if
  
  end subroutine sbwIndex