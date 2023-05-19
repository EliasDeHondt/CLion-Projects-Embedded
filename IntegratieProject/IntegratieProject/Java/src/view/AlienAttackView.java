/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

package view;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;

public class AlienAttackView extends GridPane {
    // Attributes
    private ImageView[] segmentOnHorizontal;
    private ImageView[] segmentOffHorizontal;
    private ImageView[] segmentOnVertical;
    private ImageView[] segmentOffVertical;

    // Constructors
    public AlienAttackView() {
        this.initialiseNodes();
        this.setStyle();
        this.layoutNodes();
    }

    // Methods
    private void initialiseNodes() {
        this.segmentOnHorizontal = new ImageView[12];
        this.segmentOffHorizontal = new ImageView[12];
        this.segmentOnVertical = new ImageView[16];
        this.segmentOffVertical = new ImageView[16];
        for (int i = 0; i < 12; i++) {
            this.segmentOnHorizontal[i] = new ImageView(new Image("/img/segmentOnHorizontal.png"));
            this.segmentOffHorizontal[i] = new ImageView(new Image("/img/segmentOffHorizontal.png"));
        }
        for (int i = 0; i < 16; i++) {
            this.segmentOnVertical[i] = new ImageView(new Image("/img/segmentOnVertical.png"));
            this.segmentOffVertical[i] = new ImageView(new Image("/img/segmentOffVertical.png"));
        }
    }

    private void setStyle() {
        this.setHgap(10);
        this.setVgap(10);
        this.setStyle("""
                -fx-background-color: #4F94F0;
                -fx-padding: 10px;
                """);
    }

    public void layoutNodes() {
        // Display 1
        this.add(this.segmentOffHorizontal[0], 1, 0); // Segment A
        this.add(this.segmentOffVertical[0], 0, 1); // Segment F
        this.add(this.segmentOffVertical[1], 2, 1); // Segment B
        this.add(this.segmentOffHorizontal[1], 1, 2); // Segment G
        this.add(this.segmentOffVertical[2], 0, 3); // Segment E
        this.add(this.segmentOffVertical[3], 2, 3); // Segment C
        this.add(this.segmentOffHorizontal[2], 1, 4); // Segment D

        // Display 2
        this.add(this.segmentOffHorizontal[3], 4, 0); // Segment A
        this.add(this.segmentOffVertical[4], 3, 1); // Segment F
        this.add(this.segmentOffVertical[5], 5, 1); // Segment B
        this.add(this.segmentOffHorizontal[4], 4, 2); // Segment G
        this.add(this.segmentOffVertical[6], 3, 3); // Segment E
        this.add(this.segmentOffVertical[7], 5, 3); // Segment C
        this.add(this.segmentOffHorizontal[5], 4, 4); // Segment D

        // Display 3
        this.add(this.segmentOffHorizontal[6], 7, 0); // Segment A
        this.add(this.segmentOffVertical[8], 6, 1); // Segment F
        this.add(this.segmentOffVertical[9], 8, 1); // Segment B
        this.add(this.segmentOffHorizontal[7], 7, 2); // Segment G
        this.add(this.segmentOffVertical[10], 6, 3); // Segment E
        this.add(this.segmentOffVertical[11], 8, 3); // Segment C
        this.add(this.segmentOffHorizontal[8], 7, 4); // Segment D

        // Display 4
        this.add(this.segmentOffHorizontal[9], 10, 0); // Segment A
        this.add(this.segmentOffVertical[12], 9, 1); // Segment F
        this.add(this.segmentOffVertical[13], 11, 1); // Segment B
        this.add(this.segmentOffHorizontal[10], 10, 2); // Segment G
        this.add(this.segmentOffVertical[14], 9, 3); // Segment E
        this.add(this.segmentOffVertical[15], 11, 3); // Segment C
        this.add(this.segmentOffHorizontal[11], 10, 4); // Segment D
    }

    public ImageView[] getSegmentOnHorizontal() {
        return this.segmentOnHorizontal;
    }

    public ImageView[] getSegmentOffHorizontal() {
        return this.segmentOffHorizontal;
    }

    public ImageView[] getSegmentOnVertical() {
        return this.segmentOnVertical;
    }

    public ImageView[] getSegmentOffVertical() {
        return this.segmentOffVertical;
    }

    public GridPane getGridPane() {
        return this;
    }
}
