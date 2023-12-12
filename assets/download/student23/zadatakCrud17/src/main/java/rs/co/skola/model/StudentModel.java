package rs.co.skola.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name="student")
public class StudentModel {
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private Long id;
	@Column(name="ime_studenta",  columnDefinition = "VARCHAR(25)", nullable = false)
	private String ime;
	@Column(name="prezime",  columnDefinition = "VARCHAR(25)", nullable = false)
	private String prezime;
	@Column(name="email",  columnDefinition = "VARCHAR(255)", nullable = true)
	private String email;
	//get set construktor prazan konstruktor za sve parametre
	//hash and equal
	public Long getId() {
		return id;
	}
	public void setId(Long id) {
		this.id = id;
	}
	public String getIme() {
		return ime;
	}
	public void setIme(String ime) {
		this.ime = ime;
	}
	public String getPrezime() {
		return prezime;
	}
	public void setPrezime(String prezime) {
		this.prezime = prezime;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public StudentModel(Long id, String ime, String prezime, String email) {
		super();
		this.id = id;
		this.ime = ime;
		this.prezime = prezime;
		this.email = email;
	}
	public StudentModel() {
		super();
		// TODO Auto-generated constructor stub
	}
	public void azuriraj(StudentModel student) {
		this.ime = student.getIme();
		this.prezime = student.getPrezime();
		this.email = student.getEmail();
		
		
	}
	
}
