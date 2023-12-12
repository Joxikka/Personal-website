package rs.co.skola.controller;

import java.util.List;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import rs.co.skola.model.StudentModel;
import rs.co.skola.service.StudentService;
import rs.co.skola.service.impl.StudentServiceImpl;

@RestController
public class StudentController {
	private StudentService studentService;

	public StudentController(StudentService studentService) {
		super();
		this.studentService = studentService;
	}
	
	// http://localhost:8080/save OK
	@PostMapping("/save")
	public ResponseEntity<StudentModel> sacuvajStudenta(
			@RequestBody StudentModel student
			){
		return new ResponseEntity<StudentModel>(
				studentService.save(student), HttpStatus.CREATED);
	}
	
	@GetMapping("lista")
	public List<StudentModel>
		listaStudenata(){
			return studentService.listaStudenata();	
	}
	
	
	//http://localhost:8080/getStudent/1
	@GetMapping("/getStudent/{idStudenta}")
	public ResponseEntity<StudentModel>
		vratiStudenta(
				@PathVariable("idStudenta") Long id
				){
		return new ResponseEntity<StudentModel>(studentService.getStudent(id), HttpStatus.OK);
	}
	
	@PutMapping("/update.{idStudenta}")
	public ResponseEntity<StudentModel>
		azurirajStudenta(
				@PathVariable("idStudenta") Long id,
				@RequestBody StudentModel student
				){
		return new ResponseEntity<StudentModel>
		(studentService.update(student, id), HttpStatus.OK);
	}
		
	
	
	
}
