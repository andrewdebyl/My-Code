import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class ScoreCalc {

    private ArrayList<Difficulty> difficulties = new ArrayList<>();


    public ScoreCalc() {
    }

    public ScoreCalc(String filename) {
        try {
            File file = new File(filename);
            Scanner reader = new Scanner(file);
            String dificultyTxt[] = reader.nextLine().split(",");
            int dificultyLevel[] = {Integer.parseInt(dificultyTxt[0].trim()), Integer.parseInt(dificultyTxt[1].trim()), Integer.parseInt(dificultyTxt[2].trim())};
            while (reader.hasNextLine()) {
                String line = reader.nextLine();
                String[] datas = line.split(",");
                String playerId = datas[0].trim();
                String dificulty = datas[1].trim();
                int challenge = Integer.parseInt(datas[2].trim());
                double baseScore = Double.parseDouble(datas[3].trim());
                int coinsFound = Integer.parseInt(datas[4].trim());
                double timeTaken = Double.parseDouble(datas[5].trim());
                int liveLost = Integer.parseInt(datas[6].trim());
                Difficulty d = null;
                int dificultyConstant = 0;
                if (dificulty.equalsIgnoreCase("e")) {
                    d = new Easy();
                    dificultyConstant = dificultyLevel[0];
                    ((Challenged) d).setNumChallengesComplete(challenge);
                } else if (dificulty.equalsIgnoreCase("h")) {
                    d = new Heroic();
                    dificultyConstant = dificultyLevel[1];
                    ((Challenged) d).setNumChallengesComplete(challenge);
                } else {
                    d = new HardCore();
                    dificultyConstant = dificultyLevel[2];
                }
                d.setPlayerID(playerId);
                d.setBaseScore(baseScore);
                d.setCoinsFound(coinsFound);
                d.setDifficultyConstant(dificultyConstant);
                d.setLiveLost(liveLost);
                d.setTimeTaken(timeTaken);
                difficulties.add(d);
            }
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.println(filename + " file not found!");
        }
    }

    public double getScore(String playerID)
    {
        Difficulty res=null;
        for (Difficulty difficulty : difficulties) {
            if(difficulty.getPlayerID().equals(playerID))
            {
                res=difficulty;
                break;
            }
        }
        if(res==null)
            return 0;

        return res.getLeaderBoardScore();
    }

    public String toString() {
        String output="";
        for (Difficulty difficulty : difficulties) {
            output+=difficulty.toString()+"\n";
        }
        return output;
    }
}