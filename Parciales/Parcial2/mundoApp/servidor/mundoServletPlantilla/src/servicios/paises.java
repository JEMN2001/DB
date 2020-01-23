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

		try (Connection conexion = DriverManager.getConnection("jdbc:postgresql://localhost:5432/world", "postgres", "postgres")) {
			Statement statement = conexion.createStatement();
			String atributos = "surfacearea, population";
			String relacion = "public.country";
			String condicion = "name='"+pais+"'";
			ResultSet resultset = statement.executeQuery("select "+ atributos +" from "+ relacion +" where "+ condicion +";");
			area = resultset.getString("surfacearea");
			poblacion = resultset.getString("population");
			conexion.close();
		}
		catch (SQLException e) {
			System.out.println("Conexion fallida");
			e.printStackTrace();
		}
		//End of my code

		out.println("<HEAD><TITLE> Datos del Mundo</TITLE></HEAD>");
		out.println("<BODY>");
		out.println("<h1>Mundo App </h1>");
		out.println("Aqu� encontrar�s informaci�n de todos los pa�ses del mundo. </br></br>");
		out.println("Escribe el nombre del pa�s para obtener su �rea y poblaci�n. </br></br>");
		out.println("<form action=\"http://localhost:8080/mundo/servicios/paises\" method=get>");
		out.println("Nombre del pa�s: <input type=text size=20 name=\"pais\">");
		out.println("<input type=submit value=\"Enviar\">");
		out.println("</form>");



		out.println("<table BORDER COLS=3>");
		out.println(" <tr> <td>Pa�s</td> <td>�rea</td> <td>Poblaci�n</td> </tr>");

		//My code
		out.println("<tr> <td>"+ pais +"</td> <td>"+ area +"</td> <td>"+ poblacion +"</td> </tr>");
		//End of my code

		out.println("</table>");
		out.println("</BODY>");
		out.close();
	}
}
