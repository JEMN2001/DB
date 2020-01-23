package testServlet;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/testServlet/consultaCurso")
public class ConsultaCursosServlet extends HttpServlet{

	public void doGet(HttpServletRequest request,
	HttpServletResponse response)
	throws ServletException, IOException
	{
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();

		out.println("<HEAD><TITLE> Query Result</TITLE></HEAD>");
		out.println("<BODY>");
		String persontype = request.getParameter("tipoParam_cur");
		//String number = request.getParameter("nombre");
		out.println("<table BORDER COLS=3>");
		out.println(" <tr> <td>ID</td> <td>Nombre: </td>" +
				" <td>Creditos</td> </tr>");
		String ID;
		String nombre;
		String creditos;
		if(persontype.equals("Nombre")) {
			ID = "2121";
			nombre = request.getParameter("value");
			creditos = "3";
		}
		else {
			ID = request.getParameter("value");
			nombre = "Lógica 2";
			creditos = "2";
		}
		out.println("<tr> <td>" + ID + "</td>" +
				"<td>" + nombre + "</td>" +
				"<td>" + creditos + "</td></tr>");

		out.println("</table>");
		out.println("</BODY>");
		out.close();
	}
}
