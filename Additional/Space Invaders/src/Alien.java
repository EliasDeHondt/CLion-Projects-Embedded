/**
 * Van Elias De Hondt
 * 5/11/2022
 */

public class Alien extends Character {
    // Attributen
    public boolean moveRight;
    public boolean moveLeft;
    public boolean isVisible;
    // Constructor
    public Alien(int x, int y, int speed) {
        super(x, y, speed);
        this.moveRight = true;
        this.moveLeft = false;
        this.isVisible = true;
    }
    // Methode
}
