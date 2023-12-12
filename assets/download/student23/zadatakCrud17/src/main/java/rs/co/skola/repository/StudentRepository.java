package rs.co.skola.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import rs.co.skola.model.StudentModel;

public interface StudentRepository extends JpaRepository<StudentModel, Long> {

}
