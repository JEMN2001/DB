import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class EjemploConexionPostgreSQL_taller5 {
    public static void main(String[] args) {
    	
    	//Intenta establecer conexion
    	System.out.println("Estableciendo conexion...");
        try (Connection conexion = DriverManager.getConnection("jdbc:postgresql://localhost:5432/taller3", "postgres", "postgres")) {
 
            
            System.out.println("Conexion con la base de datos establecida (PostgreSQL)");
            Statement statement = conexion.createStatement();
            
            
           //Ejemplo 1 consulta parametrizada
            System.out.println("Consultando la base de datos...");
            String atributos = "nombre, nombre_unid, creditos";  
            String relacion = "public.curso";
            String condicion = "nombre_unid = 'BIOL'"; 
            ResultSet resultSet = statement.executeQuery("select "+atributos+"  from "+relacion+ " where "+condicion+";");
            
            System.out.println("Imprimiendo resultados...");
            System.out.printf("%-30.30s  %-30.30s %-30.30s%n", "Nombre", "Unidad", "# creditos");
            while (resultSet.next()) {
                System.out.printf("%-30.30s  %-30.30s  %-30.30s%n", resultSet.getString("nombre"), resultSet.getString("nombre_unid"), resultSet.getString("creditos"));
            }
            System.out.println();
            
            //Ejemplo 2 consulta parametrizada - inyeccion
            System.out.println("Consultando la base de datos...");
            //String unidad = "BIOL";  
            String unidad = "BIOL' or 'A'='A";
            resultSet = statement.executeQuery("select nombre, nombre_unid, creditos "
            				+ " from public.curso where nombre_unid ='"+unidad+"';");
            
            System.out.println("Imprimiendo resultados...");
            System.out.printf("%-30.30s  %-30.30s %-30.30s%n", "Nombre", "Unidad", "# creditos");
            while (resultSet.next()) {
                System.out.printf("%-30.30s  %-30.30s  %-30.30s%n", resultSet.getString("nombre"), resultSet.getString("nombre_unid"), resultSet.getString("creditos"));
            }
            
            //Ejemplo 3 consulta parametrizada - instruccion preparada
            System.out.println("Consultando la base de datos...");
            PreparedStatement prepStatement = conexion.prepareStatement("select nombre, nombre_unid, creditos "
    				+ " from public.curso where nombre_unid = ?");
            unidad = "BIOL";  
            unidad = "BIOL' or 'A'='A";
            prepStatement.setString(1,unidad);
            resultSet = prepStatement.executeQuery();
            
            System.out.println("Imprimiendo resultados...");
            System.out.printf("%-30.30s  %-30.30s %-30.30s%n", "Nombre", "Unidad", "# creditos");
            while (resultSet.next()) {
                System.out.printf("%-30.30s  %-30.30s  %-30.30s%n", resultSet.getString("nombre"), resultSet.getString("nombre_unid"), resultSet.getString("creditos"));
            }
            
            conexion.close();
            
            
            
        } catch (SQLException e) {
            System.out.println("Conexion fallida");
            e.printStackTrace();
        }
    }

}



 
