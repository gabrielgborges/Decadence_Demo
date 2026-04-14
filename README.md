# Decadence — UE5 Gameplay Demo (C++)

A vertical slice of a **horror game** with fixed cameras showcasing production-grade Unreal Engine 5 C++: 
async assetstreaming with stale-load guards, interface-driven interaction, CommonUI-backed
static-camera framing, and strict ownership semantics throughout.

## Highlights

- **Async, memory-safe item loading.** `UItemData` (a `UPrimaryDataAsset`) holds mesh, material, and input action as `TSoftObjectPtr`; `AInteractableItem` streams them via `FStreamableHandle`, guarding against stale completions with an `ExpectedAssetName` token and cancelling pending loads in `BeginDestroy`.

- **Abstracted Interaction system.** `IInteractableInterface` exposes `AllowInteraction` / `DenyInteraction` / `Interact` as `BlueprintNativeEvent`s, fully decoupling the player from concrete item types and allowing extension from either C++ or Blueprint.

- **Data-driven item management.** Items are defined entirely by `UItemData` assets — no hardcoded content — and the `FOnInteractionAllowed` delegate broadcasts an `FDataTableRowHandle` so designers author input prompts in a DataTable with zero C++ changes.

- **Modern smart pointers.** `TObjectPtr` for owned UPROPERTY refs, `TWeakObjectPtr` for non-owning observers (`CurrentInteractable`, cached `UEnhancedInputComponent`), `TSoftObjectPtr` for deferred content, `TSharedPtr<FStreamableHandle>` for streaming lifetimes — zero raw `new`/`delete`.

- **Abstract base + specialization.** `ADecadentCharacterBase` is `UCLASS(Abstract)`; `ADecadentPlayerCharacter` and `ADecadenceEnemyCharacter` specialize it — shared behavior in one place, base class never instantiable.

- **Enhanced Input, bound in C++.** Player caches `FEnhancedInputActionEventBinding` for the interact action so bindings tear down cleanly across possession changes instead of leaking.

- **CommonUI static-camera system.** `AStaticCameraTrigger` (box volume + `ACameraActor` + configurable `EViewTargetBlendFunction`) drives `UStaticCameraManagerComponent`, which fires typed multicast delegates carrying `TSubclassOf<UCommonActivatableWidget>` — the widget stack owns its lifecycle, the component only signals intent.


**Modules:** `Core`, `CoreUObject`, `Engine`, `InputCore`, `UMG`, `CommonUI`,
`EnhancedInput`, `GameplayTags`.

## Stack

Unreal Engine 5 · C++ · CommonUI · Enhanced Input · UMG · GameplayTags ·
Streamable Manager

**Note:** No AI tool was used for the development of the code. AI tools were only used as a research tool to dive-in into technical functionalities, identify possible bug causes and write documentation.

---
© Gabriel Borges. All rights reserved — contact for licensing.
