package com.example.webfluxapp.test.controller;

import com.example.webfluxapp.test.models.User;
import com.example.webfluxapp.test.services.UserService;
import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

@RequestMapping("user")
@AllArgsConstructor
@RestController
public class UserController {
    @Autowired
    private UserService userService;
    @GetMapping
    public Flux<User> getAll() {
        return userService.getAll();
    }
    @GetMapping("{id}")
    public Mono<User> getById(@PathVariable("id") final String id) {
        return userService.getById(id);
    }
    @PutMapping("{id}")
    public Mono updateById(@PathVariable("id") final String id, @RequestBody final User user) {
        return userService.update(id, user);
    }
    @PostMapping
    public Mono save(@RequestBody final User user) {
        return userService.save(user);
    }
    @DeleteMapping("{id}")
    public Mono delete(@PathVariable final String id) {
        return userService.delete(id);
    }
}
