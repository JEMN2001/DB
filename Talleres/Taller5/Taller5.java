import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class Taller5 {
	public static void main(String[] args) {
		System.out.println("Intentando establecer conexion");
		try (Connection conexion = DriverManager.getConnection("jdbc:postgresql://localhost:5432/taller5a", "postgres", "postgres")) {
			System.out.println("Conectado a la base de datos");
			Statement statement = conexion.createStatement();
			String in;
			Scanner sc = new Scanner(System.in);
			System.out.println("Ingrese el id del usuario que quiere consultar");
			in = sc.nextLine();
			sc.close();
			System.out.println("Consultando la base de datos...");
			String atributos = "nombre as curso, nota";  
            String relacion = "public.estcursos natural join public.curso";
            String condicion = "estid = '"+in+"'"; 
            ResultSet resultSet = statement.executeQuery("select "+atributos+"  from "+relacion+ " where "+condicion+";");
            System.out.println("Imprimiendo resultados...");
            System.out.printf("%-30.30s  %-30.30s%n", "curso", "nota");
            System.out.println("----------------------------------------");
            while (resultSet.next()) {
                System.out.printf("%-30.30s  %-30.30s%n", resultSet.getString("curso"), resultSet.getString("nota"));
            }
            System.out.println();
		}
		catch (SQLException e) {
			System.out.println("Conexion fallida");
            e.printStackTrace();
		}
	}
}
