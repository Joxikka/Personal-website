package rs.co.skola.service;

import java.util.List;

import rs.co.skola.model.StudentModel;

public interface StudentService {
	StudentModel save(StudentModel student);
	List<StudentModel> listaStudenata();
	StudentModel getStudent(Long idStudent);
	StudentModel getStudentByIme(String ime);
	StudentModel update(StudentModel student, Long id);
	void deleteStudent(Long id);
}
