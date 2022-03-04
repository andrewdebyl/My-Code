with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with ada.directories; use ada.directories;
with GNAT.OS_Lib;

with recordfile; use recordfile;

package imagepgm is

    procedure readpgm(imag: out imageP; filename: in unbounded_string);
    procedure writepgm(imag: in imageP; filename: in unbounded_string); 

end imagepgm;