package rs.co.skola.service.impl;

import java.util.List;
import java.util.Optional;

import org.springframework.stereotype.Service;

import rs.co.skola.exception.ResourceNotFoundException;
import rs.co.skola.model.StudentModel;
import rs.co.skola.repository.StudentRepository;
import rs.co.skola.service.StudentService;

@Service
public class StudentServiceImpl implements StudentService {
	private StudentRepository studentRepository;

	public StudentServiceImpl(StudentRepository studentRepository) {
		super();
		this.studentRepository = studentRepository;
	}

	@Override
	public StudentModel save(StudentModel student) {
		return  studentRepository.save(student);
		/*
		 * StudentModel x = studentRepository.save(student);
		 * return x;
		 * 
		 */
		
	}

	@Override
	public List<StudentModel> listaStudenata() {
		return studentRepository.findAll();
	}

	@Override
	public StudentModel getStudent(Long idStudent) {
//		Optional<StudentModel> student =
//		 studentRepository.findById(idStudent);
//		if(student.isPresent()) {
//			return student.get();
//		} else {
//			throw new ResourceNotFoundException
//			("Nema studenta sa ", "id", idStudent);
//		}
		return studentRepository.findById(idStudent)
				.orElseThrow(
						()-> new ResourceNotFoundException
						("Nema studenta sa ", "id", idStudent)
						);
	}

	@Override
	public StudentModel getStudentByIme(String ime) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public StudentModel update(StudentModel student, Long id) {
		// 1. pozovi studenta iz baze
		// 2. azuriraj student NE SME SE MENJATI ID
		// 3. sacuvaj promene
		StudentModel entitet = this.getStudent(id);
		//entitet.setEmail(student.getEmail());
		entitet.azuriraj(student);
//		entitet = studentRepository.save(entitet);
//		return entitet;
		return this.save(entitet);
	}

	@Override
	public void deleteStudent(Long id) {
		// TODO Auto-generated method stub
		
	}
	
}
