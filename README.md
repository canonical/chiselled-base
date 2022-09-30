# mock-rock
Exemplary repository to demonstrate the expected structure of the ROCK repositories within this organization.

Feel free to use this repository as a template for structuring your own ROCK repository. The `mock-rock` is not a public ROCK, but instead a dummy repository to mock a real ROCK repository. The organization's workflows perform dry-runs against this `mock-rock` to ensure the CI/CD pipelines are functional and healthy.

# ROCK project structure

To serve as an example, here's how this repository's `channel` branches are structures:

```bash
mock-rock/
├── LICENSE
├── mock-one
│   ├── Dockerfile.22.04
│   ├── Dockerfile.22.10
│   ├── LICENSE
│   ├── README.md
│   └── src
│       └── my-mock-one-source-code.md
├── mock-two
│   ├── Dockerfile.22.04
│   ├── Dockerfile.22.10
│   ├── LICENSE
│   ├── README.md
│   └── tests
│       └── my-mock-two-specific-tests.md
├── README.md
├── rockcraft.1.mock-one_22.04_build.yaml
├── rockcraft.1.mock-one_22.10_build.yaml
├── rockcraft.2.mock-two_22.04_build.yaml
├── rockcraft.2.mock-two_22.10_build.yaml
└── tests
    └── my-project-tests.md
```

# Additional information

If you'd like to know more about "branch naming conventions", "ROCK promotion processes", "triggering new ROCK builds", etc., please have a look into the [ubuntu-rocks organization profile](https://github.com/ubuntu-rocks).
