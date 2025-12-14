# The Core Elements
## Container
### Definition
- A container stores components (data) for entities (IDs). Think of it as a Map from entity IDs -> component data.

- You create a container via the ChestnutContainer class in [here](../src/core/ChestnutContainer) (silly, ikr)

### Methods
- set(id: ContainerID, component: T)
- get(id: ContainerID)
- delete(id: ContainerID)

### Example:

```ts
type Position = { x: number; y: number };

// Create a container
const positionContainer = new ChestnutContainer<Position>();

// Add a component for an entity
// entity1 is the ID, { x, y } is the component
positionContainer.add('entity1', { x: 100, y: -100 });

// Retrieve component
const elementPosition = positionContainer.get('entity1');
console.log(elementPosition); // { x: 100, y: -100 }

// Delete component
positionContainer.del('entity1');
```

## Manager
- A manager is the “god object” that knows about all containers and all hooks. It can bundle components for an entity, and hooks can operate on it.
- hooks is an object that has HazelnutHooks in it
- containers is an object that has ChestnutContainers in it
- you create a manager via the MacademiaManager class in [here](../src/core/MacademiaManager)
**NOTE**: you have to pass the ContainerMap Generic to the constructor so that it knows the Containers layout
### Methods + how to call
Class for reference: MacademiaManager<C extends ContainerMap>
- addContainer<K extends keyof C>(name: K, container: ChestnutContainer<C[K]>)
- addHook(name: string, hook: HazelnutHook<C>)
- getEntity(id: EntityID)

### Example:

```ts
type ContainerMap = {
  position: { x: number; y: number };
  health: number;
};

// Create a manager
const manager = new MacademiaManager<ContainerMap>();

// Create and add containers
const positionContainer = new ChestnutContainer<{ x: number; y: number }>();
const healthContainer = new ChestnutContainer<number>();
manager.addContainer('position', positionContainer);
manager.addContainer('health', healthContainer);

// Add entities
positionContainer.add('entity1', { x: 10, y: 20 });
healthContainer.add('entity1', 100);

// Retrieve a full entity bundle
const entity = manager.getEntity('entity1'); // getEntity bundles all components for the given ID
console.log(entity);
// Output: { position: { x: 10, y: 20 }, health: 100 }
```

## Hook
### Definition
A hook keeps track of which entities are “active” at any given moment. It stores two things:
1. culls functions that take a bunch of entity IDs and return a filtered list of IDs that are still relevant.
  - think of it like a filter, each cull function filters out the ids that don't pass certain requirements
2. ActiveIDs is the final list of entities that survived the culls
- You create a hook using the HazelnutHook class in [here](../src/core/HazelnutHook) (veri silly)
**NOTE**: you have to pass the ContainerMap Generic to the constructor so that the hook knows the manager's containers
### Methods
  - addCull(fn: CullFn)
  - run(initalIDs: string[], manager: MacademiaManager<C>)
  - runFunc(fn: (id: string) => void)
  - getActiveIDs()

### Example:
```ts
type ContainerMap = {
  position: { x: number; y: number };
  health: number;
};

// Create a manager first
const manager = new MacademiaManager<ContainerMap>();

// Add some containers
const positionContainer = new ChestnutContainer<{ x: number; y: number }>();
const healthContainer = new ChestnutContainer<number>();

manager.addContainer('position', positionContainer);
manager.addContainer('health', healthContainer);

// Add an entity
positionContainer.add('entity1', { x: 0, y: 0 });
healthContainer.add('entity1', 100);

// Create a hook
const aliveHook = new HazelnutHook<ContainerMap>();

// Add a cull function: only entities with health > 0
aliveHook.addCull((ids, mgr) =>
  ids.filter(id => (mgr.getEntity(id).health ?? 0) > 0)
);

// Add hook to manager
manager.addHook('alive', aliveHook);

// Run the hook on a set of IDs
aliveHook.run(['entity1', 'entity2'], manager);

// Run a function on active IDs
aliveHook.runFunc(id => {
  console.log('Active entity:', id, manager.getEntity(id));
});
```