import java.util.Scanner;

public class TestGame {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the file name: ");
        String fileName = sc.nextLine();
        ScoreCalc calc = new ScoreCalc(fileName);
        System.out.println(calc);
    }
}