package com.example.spring_test_mvc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class SimpleController {
	
    @RequestMapping("simplePrintOutMethod")
    @ResponseBody
	public String simplePrintOutMethod() {
		return "This is simplePrintOutMethod.";
	}
    
    @RequestMapping("simpleHtmlMaking")
    @ResponseBody
	public String simpleHtmlMaking() {
		
    	StringBuffer sb = new StringBuffer();
    	sb.append("<html>");
    	sb.append("<head>");
    	sb.append("<title>This is HTML Page</title>");
    	sb.append("</head>");
    	sb.append("<body>");
    	sb.append("Print Message");
    	sb.append("</body>");
    	sb.append("</html>");
    	
    	return sb.toString();
	}
    
	@RequestMapping("simpleMethod")
	public String simpleJsp() {
		return "simplePage";
	}
    

}
