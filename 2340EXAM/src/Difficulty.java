public class Difficulty {
    private String playerID;
    private double baseScore;
    private int coinsFound;
    private double timeTaken;
    private double difficultyConstant;
    private int liveLost;


    public Difficulty() {
    }

    public double getLeaderBoardScore() {
        double leaderBoardScore = (getBaseScore() + getCoinsFound()) - (getTimeTaken() * getDifficultyConstant());
        double score=leaderBoardScore;
        if(this instanceof Easy)
        {
            leaderBoardScore-=(getLiveLost() * getDifficultyConstant());
            score=leaderBoardScore+((Challenged) this).getBonusScore();
        }
        else if(this instanceof Heroic)
        {
            leaderBoardScore-=(getLiveLost() * getDifficultyConstant());
            score=leaderBoardScore+((Challenged) this).getBonusScore();
        }
        return score;
    }

    public double getBaseScore() {
        return baseScore;
    }

    public void setBaseScore(double baseScore) {
        this.baseScore = baseScore;
    }

    public int getCoinsFound() {
        return coinsFound;
    }

    public void setCoinsFound(int coinsFound) {
        this.coinsFound = coinsFound;
    }

    public double getTimeTaken() {
        return timeTaken;
    }

    public void setTimeTaken(double timeTaken) {
        this.timeTaken = timeTaken;
    }

    public double getDifficultyConstant() {
        return difficultyConstant;
    }

    public void setDifficultyConstant(double val) {
        difficultyConstant = val;
    }

    public String getPlayerID() {
        return playerID;
    }

    public void setPlayerID(String playerID) {
        this.playerID = playerID;
    }

    public void setLiveLost(int liveLost) {
        this.liveLost = liveLost;
    }

    public int getLiveLost() {
        return liveLost;
    }

    public String toString() {
        return playerID +","+(int)getLeaderBoardScore();
    }
}
