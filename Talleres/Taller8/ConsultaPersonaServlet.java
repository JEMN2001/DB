package testServlet;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/testServlet/consultaPersona")
public class ConsultaPersonaServlet extends HttpServlet{

	public void doGet(HttpServletRequest request,
	HttpServletResponse response)
	throws ServletException, IOException
	{
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		
		out.println("<HEAD><TITLE> Query Result</TITLE></HEAD>");
		out.println("<BODY>");
		String persontype = request.getParameter("tipoPersona");
		//String number = request.getParameter("nombre");
		out.println("<table BORDER COLS=3>");
		out.println(" <tr> <td>ID</td> <td>Nombre: </td>" +
				" <td>Departamento</td> </tr>");
		int ID;
		String nombre;
		String depto;
		if(persontype.equals("estudiante")) {
			ID = 8888;
			nombre = "Juan";
			depto = "MACC";
		}
		else {
			ID = 2222;
			nombre = "Renato";
			depto = "MACC";
		}
		out.println("<tr> <td>" + ID + "</td>" +
				"<td>" + nombre + "</td>" +
				"<td>" + depto + "</td></tr>");
			
		out.println("</table>");
		out.println("</BODY>");
		out.close();
	}
}