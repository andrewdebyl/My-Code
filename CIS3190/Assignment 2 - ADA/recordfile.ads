with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with ada.directories; use ada.directories;
with GNAT.OS_Lib;

--Seperate package to hold the record

package recordfile is
    type imageStruct is array (1..500, 1..500) of integer;

    type imageP is
        record
            picture : imageStruct;
            dimenx : integer;
            dimeny : integer;
            maxVal : integer;
        end record;
        
end recordfile;