package testServlet;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/testServlet/consultaEstudiante")
public class ConsultaEstudianteServlet extends HttpServlet{

	public void doGet(HttpServletRequest request,
	HttpServletResponse response)
	throws ServletException, IOException
	{
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();

		out.println("<HEAD><TITLE> Query Result</TITLE></HEAD>");
		out.println("<BODY>");
		String persontype = request.getParameter("tipoParam_Per");
		//String number = request.getParameter("nombre");
		out.println("<table BORDER COLS=3>");
		out.println(" <tr> <td>ID</td> <td>Nombre: </td>" +
				" <td>Apellido</td> </tr>");
		String ID;
		String nombre;
		String Apellido;
		if(persontype.equals("Nombre")) {
			ID = "8888";
			nombre = request.getParameter("value");
			Apellido = "Perez";
		}
		else if (persontype.equals("Apellido")){
			ID = "2222";
			nombre = "Renato";
			Apellido = request.getParameter("value");
		}
		else {
			ID = request.getParameter("value");
			nombre = "Pablo";
			Apellido = "Escobar";
		}
		out.println("<tr> <td>" + ID + "</td>" +
				"<td>" + nombre + "</td>" +
				"<td>" + Apellido + "</td></tr>");

		out.println("</table>");
		out.println("</BODY>");
		out.close();
	}
}
