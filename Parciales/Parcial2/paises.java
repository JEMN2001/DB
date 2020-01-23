package servicios;

import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.SQLException;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/servicios/paises")
public class paises extends HttpServlet{

	public void doGet(HttpServletRequest request,
	HttpServletResponse response)
	throws ServletException, IOException
	{
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();

		//My code
		String pais = request.getParameter("pais");
		String area = "";
		String poblacion = "";

		try (Connection conexion = DriverManager.getConnection("jdbc:postgresql://localhost:5432/world", "juane", "9910")) {
			Statement statement = conexion.createStatement();
			String atributos = "surfacearea, population";
			String relacion = "public.country";
			String condicion = "name='"+pais+"'";
			ResultSet resultset = statement.executeQuery("select "+ atributos +" from "+ relacion +" where "+ condicion +";");
			resultset.next();
			area = resultset.getString("surfacearea");
			poblacion = resultset.getString("population");
			conexion.close();
		}
		catch (SQLException e) {
			System.out.println("Conexion fallida");
			e.printStackTrace();
		}
		//End of my code
		out.println("<html>");
		out.println("<HEAD><TITLE> Datos del Mundo</TITLE><meta charset=\"UTF-8\"/></HEAD>");
		out.println("<BODY>");
		out.println("<h1>Mundo App </h1>");
		out.println("Aquí encontrarás información de todos los países del mundo. </br></br>");
		out.println("Escribe el nombre del país para obtener su área y población. </br></br>");
		out.println("<form action=\"http://localhost:8080/test/servicios/paises\" method=get>");
		out.println("Nombre del país: <input type=text size=20 name=\"pais\">");
		out.println("<input type=submit value=\"Enviar\">");
		out.println("</form>");



		out.println("<table BORDER COLS=3>");
		out.println(" <tr> <td>País</td> <td>área</td> <td>Población</td> </tr>");

		//My code
		out.println("<tr> <td>"+ pais +"</td> <td>"+ area +"</td> <td>"+ poblacion +"</td> </tr>");
		//End of my code

		out.println("</table>");
		out.println("</BODY>");
		out.println("</html>");
		out.close();
	}
}
