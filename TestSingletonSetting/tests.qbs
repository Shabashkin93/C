import qbs

Application {
    name: "tests"
    files: ["*.cpp", "*.h"]
    Depends {
        name : "cpp"
    }
    Depends {
        condition: project.enableUnitTests;
        name: "Qt.test"
    }
}
