///
/// Composition is "has-a" relationship between classes.
/// Helps create a more modular code.
///

#include <cassert>
#include <iostream>
#include <string>

/// The class Name contains family and given names.
class Name
{
public:
  Name(const std::string givenName, const std::string familyName)
    : givenName_(givenName)
    , familyName_(familyName)
  {
  }

  ~Name()
  {}

  std::string
  getName() const
  {
    return (givenName_ + " " + familyName_);
  }

private:
  std::string givenName_;
  std::string familyName_;
};


/// Declaration (definition) of the class Student
/// The Student has a Name
class Student
{
public:
  /// Constructor
  Student(std::string givenName, std::string familyName, int studentID)
    : name_(new Name(givenName, familyName))
    , studentID_(studentID)
  {
    // name_ = nullptr; ///< Bug!
  }

  /// Destructor
  ~Student()
  {
    delete name_; ///< Missing!
  }

  /// Return a copy of the student's ID number
  int
  getStudentID() const
  {
    return studentID_;
  }

  /// Return a copy of student's name
  std::string
  getName() const
  {
#ifdef DEBUG
    assert(name_ != nullptr);
#endif
    return name_->getName();
  }

private:
  Name *name_;      ///< Student's name
  int   studentID_; ///< Student's ID number
};


int
main(int argc, char **argv)
{
  /// Create another student (who is an instance of the Student) on the
  /// heap. Pointer p_other_student points to the instance of the other
  /// student.
  Student *p_other_student = new Student("Terry", "Jones", 111234);

  std::cout << "Student name: " << p_other_student->getName() << ", "
            << "ID#: " << p_other_student->getStudentID() << std::endl;

  /// Delete the other student
  delete p_other_student;

  return 0;
}
