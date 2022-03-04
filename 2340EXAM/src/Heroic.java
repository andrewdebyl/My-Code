public class Heroic extends Difficulty implements Challenged {

    private int numChallenges;

    public Heroic() {
    }


    public void setNumChallengesComplete(int numChallenges) {
        this.numChallenges = numChallenges;
    }


    public int getNumChallengesComplete() {
        return numChallenges;
    }


    public double getBonusScore() {
        return numChallenges * getDifficultyConstant();
    }
}