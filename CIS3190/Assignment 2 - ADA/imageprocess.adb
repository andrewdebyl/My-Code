package body imageprocess is

    procedure imageinv(imag: in out imageP) is

        begin
        --Procedure to invert the image
            for i in 1..imag.dimeny loop
               for j in 1..imag.dimenx loop
                  imag.picture(i,j) := abs(255-imag.picture(i,j));
               end loop;
            end loop;

            put_line("File has been inverted.");
            new_line;
    end;


    procedure imagelog (imag: in out imageP) is

        begin
        --Procedure to log transform the image
            for i in 1..imag.dimeny loop
               for j in 1..imag.dimenx loop
                  imag.picture(i,j) := integer(log(float(imag.picture(i,j))) * (255.0/log(255.0)));
               end loop;
            end loop;

            put_line("File has been logged.");
            new_line;
    end;


    procedure imagestretch (imag: in out imageP; imin : integer; imax : integer) is

        begin
        --Procedure to streth the image by imin and imax
            for i in 1..imag.dimeny loop
               for j in 1..imag.dimenx loop
                  imag.picture(i,j) := integer(255.0 * ((float(imag.picture(i,j) - imin) / float(imax - imin))));
               end loop;
            end loop;

            put_line("File has been stretched.");
            new_line;
    end;

   procedure makehist (imag: in imageP) is
      begin
         put_line("makeHIST function.");
   end;
   
   
   procedure histequal (imag: in imageP) is
      begin
         put_line("histEQUAL function");
   end;

end imageprocess;