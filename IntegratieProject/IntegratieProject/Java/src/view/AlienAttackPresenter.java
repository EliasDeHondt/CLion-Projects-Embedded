/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

package view;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import javafx.application.Platform;
import model.SerialArduinoConnection;

public class AlienAttackPresenter implements SerialPortDataListener {
    // Attributes
    private final SerialArduinoConnection model;
    private final AlienAttackView view;

    // Constructors
    public AlienAttackPresenter(SerialArduinoConnection model, AlienAttackView view) {
        this.model = model;
        this.view = view;
        model.addDatalistener(this);
    }

    public void resetSegment() {
        this.view.getGridPane().getChildren().clear();
        this.view.layoutNodes();
    }

    // Methods
    @Override
    public int getListeningEvents() {
        return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println(Thread.currentThread());
        if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) return;

        StringBuilder arduinoData = new StringBuilder();
        for (byte oneByte : this.model.receiveBytes()) {
            arduinoData.append((char) oneByte);
        }

        Platform.runLater(() -> {
            if (arduinoData.substring(0, "JavaData".length()).equals("JavaData")) {
                // Haal de waarden van de attributen op
                String numbersSubstring = arduinoData.substring("JavaData ".length());
                int computer_Pawn = Integer.parseInt(numbersSubstring.substring(0, 1));
                int player_Pawn = Integer.parseInt(numbersSubstring.substring(1, 2));
                int teller = Integer.parseInt(numbersSubstring.substring(2, 3));
                int down = Integer.parseInt(numbersSubstring.substring(3, 4));

                this.resetSegment(); // All Segment Off

                // Bottom line of seven segment display (Player).
                if (player_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[2], 1, 4); // Segment D Display 1
                else if (player_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[5], 4, 4); // Segment D Display 2
                else if (player_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[8], 7, 4); // Segment D Display 3
                else if (player_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[11], 10, 4); // Segment D Display 4

                if (teller == 1) {
                    if (computer_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[0], 1, 0); // Segment A Display 1
                    else if (computer_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[3], 4, 0); // Segment A Display 2
                    else if (computer_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[6], 7, 0); // Segment A Display 3
                    else if (computer_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[9], 10, 0); // Segment A Display 4
                } else if (teller == 2) {
                    if (down == 0) {
                        if (computer_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnVertical()[0], 0, 1); // Segment F Display 1
                        else if (computer_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnVertical()[4], 3, 1); // Segment F Display 2
                        else if (computer_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnVertical()[8], 6, 1); // Segment F Display 3
                        else if (computer_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnVertical()[12], 9, 1); // Segment F Display 4
                    } else if (down == 1) {
                        if (computer_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnVertical()[1], 2, 1); // Segment B Display 1
                        else if (computer_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnVertical()[5], 5, 1); // Segment B Display 2
                        else if (computer_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnVertical()[9], 8, 1); // Segment B Display 3
                        else if (computer_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnVertical()[13], 11, 1); // Segment B Display 4
                    }
                } else if (teller == 3) {
                    if (computer_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[1], 1, 2); // Segment G Display 1
                    else if (computer_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[4], 4, 2); // Segment G Display 2
                    else if (computer_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[7], 7, 2); // Segment G Display 3
                    else if (computer_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[10], 10, 2); // Segment G Display 4
                } else if (teller == 4) {
                    if (down == 0) {
                        if (computer_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnVertical()[2], 0, 3); // Segment E Display 1
                        else if (computer_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnVertical()[6], 3, 3); // Segment E Display 2
                        else if (computer_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnVertical()[10], 6, 3); // Segment E Display 3
                        else if (computer_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnVertical()[14], 9, 3); // Segment E Display 4
                    } else if (down == 1) {
                        if (computer_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnVertical()[3], 2, 3); // Segment C Display 1
                        else if (computer_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnVertical()[7], 5, 3); // Segment C Display 2
                        else if (computer_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnVertical()[11], 8, 3); // Segment C Display 3
                        else if (computer_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnVertical()[15], 11, 3); // Segment C Display 4
                    }
                } else if (teller == 5 && !(computer_Pawn == player_Pawn)) {
                    if (computer_Pawn == 0) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[2], 1, 4); // Segment D Display 1
                    else if (computer_Pawn == 1) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[5], 4, 4); // Segment D Display 2
                    else if (computer_Pawn == 2) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[8], 7, 4); // Segment D Display 3
                    else if (computer_Pawn == 3) this.view.getGridPane().add(this.view.getSegmentOnHorizontal()[11], 10, 4); // Segment D Display 4
                }
            }
        });
    }
}
