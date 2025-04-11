좋습니다! Spring의 <form:...> 태그를 사용하지 않고, 일반 HTML + JSP 표준 기술만 사용하도록 바꾸고,
“14세 미만은 이용할 수 없습니다” 라는 메시지를 출력하도록 수정하겠습니다.

⸻

1. UserForm.java – 나이 제한 14세로 수정

import jakarta.validation.constraints.NotNull;
import java.time.LocalDate;

public class UserForm {

    @NotNull(message = "생년월일은 필수 입력 항목입니다.")
    @ValidAge(min = 14, message = "14세 미만은 이용할 수 없습니다.")
    private LocalDate birthDate;

    public LocalDate getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(LocalDate birthDate) {
        this.birthDate = birthDate;
    }
}



⸻

2. form.jsp – HTML 기본 태그 + 에러 출력

<%@ page contentType="text/html; charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
    <title>회원가입</title>
    <style>
        .error { color: red; }
    </style>
</head>
<body>
    <h2>생년월일 입력</h2>

    <form action="${pageContext.request.contextPath}/submit" method="post">
        <table>
            <tr>
                <td><label for="birthDate">생년월일</label></td>
                <td><input type="date" name="birthDate" id="birthDate"
                           value="${param.birthDate != null ? param.birthDate : ''}" /></td>
            </tr>
        </table>

        <c:if test="${not empty errorMessage}">
            <p class="error">${errorMessage}</p>
        </c:if>

        <input type="submit" value="제출" />
    </form>
</body>
</html>



⸻

3. UserController.java – 수동 에러 메시지 전달

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;
import org.springframework.validation.BindingResult;

@Controller
public class UserController {

    @GetMapping("/form")
    public String showForm() {
        return "form";
    }

    @PostMapping("/submit")
    public String submitForm(@ModelAttribute @Valid UserForm form,
                             BindingResult bindingResult,
                             Model model) {
        if (bindingResult.hasErrors()) {
            // 가장 첫 번째 에러 메시지만 전달
            String errorMsg = bindingResult.getFieldError("birthDate") != null
                    ? bindingResult.getFieldError("birthDate").getDefaultMessage()
                    : "입력 오류가 있습니다.";
            model.addAttribute("errorMessage", errorMsg);
            return "form";
        }

        // 성공 처리
        return "success";
    }
}



⸻

4. 동작 결과 예시

유효하지 않은 생년월일 입력 시:

[생년월일 필드 아래]
14세 미만은 이용할 수 없습니다.



⸻

이 구조는 순수 HTML 기반이므로 JSP와 JSTL만 사용하며, Spring의 <form:input> 같은 태그를 전혀 사용하지 않습니다.
폼 검증을 수동으로 조절하고 싶을 때 이런 방식이 유용합니다.

필요하면 success.jsp도 예시로 드릴게요.