/**
 * Van Elias De Hondt
 * 5/11/2022
 */
public class Player extends Character {
    // Attributen
    public boolean moveRight;
    public boolean moveLeft;
    // Constructor
    public Player(int x, int y, int speed) {
        super(x, y, speed);
        this.moveRight = false;
        this.moveLeft = false;
    }
    // Methode
}
