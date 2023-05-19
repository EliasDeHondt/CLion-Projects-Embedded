/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import model.SerialArduinoConnection;
import view.AlienAttackPresenter;
import view.AlienAttackView;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) {
        SerialArduinoConnection connection = new SerialArduinoConnection();
        AlienAttackView view = new AlienAttackView();
        new AlienAttackPresenter(connection, view);
        primaryStage.setScene(new Scene(view));
        primaryStage.setResizable(false);
        primaryStage.getIcons().add(new Image("/img/logo.png"));
        primaryStage.setTitle("Integrated Project Embedded");
        primaryStage.show();
    }

    public static void main(String[] args) {
        Application.launch(args);
    }
}