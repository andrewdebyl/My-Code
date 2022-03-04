package body imagepgm is

procedure readpgm (imag: out imageP; filename: in unbounded_string) is
    fileP: file_type;
    temp : string(1..2);
begin
    open(fileP, in_file, to_string(filename));

    get(fileP, temp);

    --Error checking
    if (temp /= "P2") then
        put_line("Incorrect format of file.");
        GNAT.OS_Lib.OS_Exit (0);
    end if;

    --Getting dimensions
    get(fileP, imag.dimenx);
    get(fileP, imag.dimeny);
    get(fileP, imag.maxVal);

    --Getting values
    for i in 1..imag.dimeny loop
        for j in 1..imag.dimenx loop
            get(fileP, imag.picture(i,j));
        end loop;
    end loop;

    put_line("File read in.");
    new_line;

    close(fileP);
end;


procedure writepgm (imag: in imageP; filename: in unbounded_string) is
    fileP: file_type;
    count : integer := 1;
begin
    create(fileP, out_file, to_string(filename));

    --Printing dimensions
    Set_Output (fileP);
    Put_Line("P2");
    put(imag.dimenx, width => 0); 
    put(imag.dimeny, width => 4);
    new_line;
    put(imag.maxVal, width => 0); 
    new_line;
    
    --Printing values
    for i in 1..imag.dimeny loop
       for j in 1..imag.dimenx loop
          put(imag.picture(i,j), width=>(j-count+4));
          count := count + 1;   
       end loop;
       new_line;
       count := 1;
    end loop;

    Set_Output(standard_output);

    put_line("File has been written.");
    new_line;

    close(fileP);
end;

end imagepgm;