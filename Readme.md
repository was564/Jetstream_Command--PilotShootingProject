## Jetstream Command

![image6-resized.gif](./images/image6-resized.gif) | ![image7-resized.gif](./images/image7-resized.gif)
---|---|

### 프로젝트 개요

플레이어 전투기가 주변을 돌아다니며 적 전투기를 격추시키는 3D 슈팅 게임입니다.

RasterTek 튜토리얼을 참고하여 DirectX로 제작하였습니다.

### 구현 목록

- 우클릭 시 조준(Camera Swap)하는 기능을 구현하였습니다.
- FSM을 이용하여 적 전투기의 행동을 구현하였습니다. (좌회전, 우회전, 직진, 격추)
- 적 전투기 미사일 피격 시 텍스처 변경 기능을 구현하였습니다.
- 거리 계산을 이용한 Sphere Collider 구현하였습니다.
- Phong Light를 구현하였습니다.

### 패키지 버전

DirectX 11 (In Windows 11 SDK 10.0.26100.0)