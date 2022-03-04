public class Easy extends Difficulty implements Challenged {

    private int numChallenges;

    public Easy() {
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