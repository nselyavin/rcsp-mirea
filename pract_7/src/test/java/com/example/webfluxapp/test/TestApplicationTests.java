package com.example.webfluxapp.test;

import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.http.MediaType;
import org.springframework.test.web.reactive.server.WebTestClient;

import com.example.webfluxapp.test.models.User;
import com.example.webfluxapp.test.repository.UserRepository;
import com.fasterxml.jackson.databind.deser.std.StdValueInstantiator;

import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
class TestApplicationTests {

	@Autowired
	WebTestClient webTestClient;

	@MockBean
	UserRepository userRepository;


	@Test
	void testGetStudent() {
		Flux<User> productFlux = Flux.just(
				new User("sasd","bib", "bob", "test@test.ru", "3"),
				new User("sasd2","bib", "bob", "test@test.ru", "3")
		);

		Mockito.when(userRepository.findAll()).thenReturn(productFlux);
		webTestClient.get()
				.uri("/user")
				.accept(MediaType.APPLICATION_JSON)
				.exchange()
				.expectStatus().isOk()
				.expectBody()
				.jsonPath("$").isArray()
				.jsonPath("$[0].id").isEqualTo("sasd")
				.jsonPath("$[1].id").isEqualTo("sasd2");
	}

	@Test
	void testAddProduct() {
		User user = new User("sasd","bib", "bob", "test@test.ru", "3");

		Mono<User> userMono = Mono.just(user);

		Mockito.when(userRepository.save(user)).thenReturn(userMono);


		webTestClient.post()
				.uri("/user")
				.contentType(MediaType.APPLICATION_JSON)
				.body(userMono, User.class)
				.exchange()
				.expectStatus().isOk()
				.expectBody(User.class).isEqualTo(user);
	}

	@Test
	void errorTest(){
		Flux<Integer> flux  = Flux.just(1, 0, -1);
	}
}
