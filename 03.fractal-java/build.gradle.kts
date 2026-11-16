plugins {
    java
    kotlin("jvm") version "2.2.0"
}

group = "com.programacion.paralela"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {

    implementation("com.github.jnr:jnr-ffi:2.3.7")

    testImplementation(kotlin("test"))
}

kotlin {
    jvmToolchain(25)
}