package com.example.demo;

import java.time.Duration;
import java.util.concurrent.Flow.Subscriber;
import java.util.concurrent.Flow.Subscription;
import java.util.function.Consumer;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import reactor.core.publisher.BaseSubscriber;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;
import reactor.core.scheduler.Scheduler;
import reactor.core.scheduler.Schedulers;
import reactor.test.StepVerifier;

@SpringBootTest
class DemoApplicationTests {

	@Test
	void simpleFluxExample() {
		Flux<String> fluxCalc = Flux.just(-1, 0, 1)
        .map(i -> "10 / " + i + " = " + (10 / i));

    StepVerifier.create(fluxCalc)
        .expectNextCount(1)
        .expectError(ArithmeticException.class)
        .verify();
	}

	@Test
	void publishSubscribeExample() {
		Scheduler schedulerA = Schedulers.newParallel("Scheduler A");
		Scheduler schedulerB = Schedulers.newParallel("Scheduler B");
		Scheduler schedulerC = Schedulers.newParallel("Scheduler C");

		Flux.just(1)
			.map(i -> {
				System.out.println("First map " + Thread.currentThread().getName());
				return i;
			})
			.subscribeOn(schedulerA)
			.map(i -> {
				System.out.println("Second map " + Thread.currentThread().getName());
				return i;
			})
			.publishOn(schedulerB)
			.map(i -> {
				System.out.println("Third map " + Thread.currentThread().getName());
				return i;
			})
			.subscribeOn(schedulerC)
			.map(i -> {
				System.out.println("Fourth map " + Thread.currentThread().getName());
				return i;
			})
			.publishOn(schedulerA)
			.map(i -> {
				System.out.println("Fifth map " + Thread.currentThread().getName());
				return i;
			})
			.blockLast();
		
	}

	@Test
	public void backpressureExample() {

		Flux<Integer> fluxCalc = Flux.range(1,5);

		fluxCalc.log().subscribe(new BaseSubscriber<Integer>() {
			int counter; 

            // @Override
            // protected void hookOnSubscribe(Subscription s){
				
			// }

			@Override
			protected void hookOnNext(Integer value) {
				counter++;
                if (counter % 2 == 0) {
                    System.out.println("Requesting 2 emissions");
                    request(3);
					System.out.println(value);
				}

			}
		});
	}

	@Test
	public void coldPublisherExample() throws InterruptedException {
		Flux<Long> intervalFlux = Flux.interval(Duration.ofSeconds(1));

		intervalFlux.subscribe(i -> System.out.println(i));


	}

}

