with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with ada.directories; use ada.directories;
with GNAT.OS_Lib;

with imagepgm; use imagepgm;
with imageprocess; use imageprocess;
with recordfile; use recordfile;

procedure image is
    num : Integer;
    img : imageP;
    imin : Integer;
    imax : integer;

    --FUNCTION--
    function getFilename (val : character) return Unbounded_String is
        fname : Unbounded_String;
        temp : Character;
        begin
            --If we are reading from a file
            if (val = 'r') then
                put_line("Enter filename: ");
                loop
                    get_line(fname);
                    exit when exists(to_string(fname));
                end loop;

                return fname;
            else 
            -- If we are writing to a file
                put_line("Enter output filename: ");
                get_line(fname);

                if exists(to_string(fname)) then
                    Put_Line("This file already exists, overwrite? (y/n): ");
                    get (temp);

                    if temp = 'y' then
                        return fname;
                    else
                        Put_Line("Image cannot be saved then.");
                        GNAT.OS_Lib.OS_Exit (0);
                    end if;
                else
                    return fname;
                end if;
            end if;
    end getFilename;
    --END FUNCTION--

begin

    loop
        Put_Line("Image Processing");
        Put_Line("1. Read in PGM image from file");
        Put_Line("2. Apply image invertion");
        Put_Line("3. Apply LOG function");
        Put_Line("4. Apply contrast stretching");
        Put_Line("5. Write PGM image to file");
        Put_Line("6. Quit");
        Put_Line("Choice: ");
        Get (num);
        Skip_line;
    
        case num is
            when 1 =>
                readpgm(img, getFilename('r'));                
            when 2 =>
                imageinv (img);
            when 3 =>
                imagelog(img);           
            when 4 =>
                put_line("Enter the value of imin: ");
                get(imin);
                Skip_Line;
                put_line("Enter the value of imax: ");
                get(imax);

                imagestretch (img,imin,imax);
            when 5 =>
                writepgm (img, getFilename('w'));
            when others =>
                GNAT.OS_Lib.OS_Exit (0);
        end case;
    end loop;

end image;