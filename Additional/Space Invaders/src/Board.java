import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import javax.swing.Timer;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.imageio.*;
import java.awt.image.*;
import java.io.*;

/**
 * Van Elias De Hondt
 * 5/11/2022
 */

public class Board extends JPanel implements Runnable, MouseListener {
    // Attributen
    public boolean ingame = true;
    private Dimension d;
    public int BOARD_WIDTH = 500;
    public int BOARD_HEIGHT = 500;
    public int x = 0;
    public BufferedImage img;
    public String message = "Click Board to Start";
    private Thread animator;
    public Player player;
    public Alien[] aliens = new Alien[10];
    // Constructor
    public Board() {
        addKeyListener(new TAdapter());
        addMouseListener(this);
        setFocusable(true);
        d = new Dimension(BOARD_WIDTH, BOARD_HEIGHT);
        player = new Player(BOARD_WIDTH/2, BOARD_HEIGHT-60, 5);
        int alienX = 10;
        int alienY = 10;
        for (int i = 0; i < aliens.length; i++) {
            aliens[i] = new Alien(alienX, alienY, 10);
            alienX += 40;
            if (i==4) {
                alienX = 10;
                alienY += 40;
            }
        }
        setBackground(Color.black);
        if (animator == null || !ingame) {
            animator = new Thread(this);
            animator.start();
        }
        setDoubleBuffered(true);
    }
    public void paint(Graphics g) {
        super.paint(g);
        g.setColor(Color.white);
        g.fillRect(0, 0, d.width, d.height);
        g.setColor(Color.red);
        g.fillRect(player.x, player.y, 20, 20);
        if (player.moveRight==true) player.x += player.speed;
        if (player.moveLeft==true) player.x -= player.speed;
        moveAliens();
        for (int i = 0; i < aliens.length; i++) {
            g.fillRect(aliens[i].x, aliens[i].y, 20, 20);
        }
        Font small = new Font("Helvetica", Font.BOLD, 14);
        FontMetrics metr = this.getFontMetrics(small);
        g.setColor(Color.black);
        g.setFont(small);
        g.drawString(message, 10, d.height - 60);
        if (ingame) {
        }
        Toolkit.getDefaultToolkit().sync();
        g.dispose();
    }
    public void moveAliens(){
        for (int i = 0; i < aliens.length; i++) {
            if (aliens[i].moveLeft == true) aliens[i].x -= 2;// aliens[i].speed;
            if (aliens[i].moveRight == true) aliens[i].x +=2;// aliens[i].speed;
            // aliens[i].y += aliens[i].speed;
        }
        for (int i = 0; i < aliens.length; i++) {
            if (aliens[i].x > BOARD_WIDTH) {
                for (int j = 0; j < aliens.length; j++) {
                    aliens[j].moveLeft = true;
                    aliens[j].moveRight = false;
                    aliens[j].y += 5;
                }
            }
            if (aliens[i].x < 0) {
                for (int j = 0; j < aliens.length; j++) {
                    aliens[j].moveRight = true;
                    aliens[j].moveLeft = false;
                    aliens[j].y += 5;
                }
            }
        }
    }
    private class TAdapter extends KeyAdapter {
        public void keyReleased(KeyEvent e) {
            int key = e.getKeyCode();
            player.moveRight = false;
            player.moveLeft = false;
        }
        public void keyPressed(KeyEvent e) {
            int key = e.getKeyCode();
            if (key == 39) {
                player.moveRight = true;
            }
            if (key == 37) {
                player.moveLeft = true;
            }
        }
    }
    public void mousePressed(MouseEvent e) {
        int x = e.getX();
        int y = e.getY();
    }
    public void mouseReleased(MouseEvent e) {
    }
    public void mouseEntered(MouseEvent e) {
    }
    public void mouseExited(MouseEvent e) {
    }
    public void mouseClicked(MouseEvent e) {
    }
    public void run() {
        long beforeTime, timeDiff, sleep;
        beforeTime = System.currentTimeMillis();
        int animationDelay = 5;
        long time =
                System.currentTimeMillis();
        while (true) {
            repaint();
            try {
                time += animationDelay;
                Thread.sleep(Math.max(0, time -
                        System.currentTimeMillis()));
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }
}
