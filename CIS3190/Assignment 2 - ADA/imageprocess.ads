with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with ada.directories; use ada.directories;
with GNAT.OS_Lib;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

with recordfile; use recordfile;

package imageprocess is

    procedure imageinv(imag: in out imageP);
    procedure imagelog (imag: in out imageP);
    procedure imagestretch (imag: in out imageP; imin : integer; imax : integer);
    procedure makehist (imag: in imageP);
    procedure histequal (imag: in imageP);

end imageprocess;