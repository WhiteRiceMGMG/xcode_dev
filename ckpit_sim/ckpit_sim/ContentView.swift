import SwiftUI

// =============================
// ギア定義
// =============================
enum Gear: String {
    case r = "R"
    case n = "N"
    case one = "1"
    case two = "2"
    case three = "3"
    case four = "4"
    case five = "5"
}

struct ContentView: View {

    @State private var sliderValue: CGFloat = 0.5
    @State private var clutchValue: CGFloat = 0.0
    @State private var brakeValue: CGFloat = 0.0
    @State private var currentGear: Gear = .n

    var body: some View {
        GeometryReader { geo in
            HStack(spacing: 0) {

                // ===== 左70% =====
                ZStack {

                    Color(red: 0.08, green: 0.12, blue: 0.20)

                    VStack {
                        HStack(alignment: .top, spacing: 40) {

                            // アクセル％
                            Text(String(format: "%.0f %%", sliderValue * 100))
                                .font(.system(size: 90, weight: .bold))
                                .foregroundStyle(.white)

                            // 現在ギア表示
                            Text(currentGear.rawValue)
                                .font(.system(size: 70, weight: .bold))
                                .foregroundStyle(.yellow)

                            Spacer()
                        }
                        .padding(.leading, 40)
                        .padding(.top, 40)

                        Spacer()
                    }

                    // シフトレバー
                    ShiftView(currentGear: $currentGear)
                        .frame(width: 220, height: 260)
                        .offset(x: -120, y: 120)

                    // ペダル群
                    VStack {
                        Spacer()
                        HStack {
                            Spacer()

                            HStack(spacing: 70) {
                                PedalView(title: "CL", value: $clutchValue)
                                
                                PedalView(title: "BR", value: $brakeValue)
                            }
                            .padding(.trailing, 40)
                            .padding(.bottom, 40)
                        }
                    }
                }
                .frame(width: geo.size.width * 0.7)

                // ===== 右30% =====
                ZStack {
                    Color(red: 0.18, green: 0.18, blue: 0.20)

                    CustomVerticalSlider(value: $sliderValue)
                        .frame(width: 60)
                        .padding(.vertical, 40)
                }
                .frame(width: geo.size.width * 0.3)
            }
        }
        .ignoresSafeArea()
    }
}



////////////////////////////////////////////////////////////
// Hパターン シフト
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// 改良版 Hパターン シフト
////////////////////////////////////////////////////////////

struct ShiftView: View {

    @Binding var currentGear: Gear
    @State private var knobPosition: CGPoint = .zero

    // 🔽 全体を約80%サイズに縮小
    let columnX: [CGFloat] = [45, 125, 205]
    let topY: CGFloat = 30
    let middleY: CGFloat = 105
    let bottomY: CGFloat = 180

    var positions: [Gear: CGPoint] {
        [
            .one: CGPoint(x: columnX[0], y: topY),
            .two: CGPoint(x: columnX[0], y: bottomY),

            .three: CGPoint(x: columnX[1], y: topY),
            .four: CGPoint(x: columnX[1], y: bottomY),

            .five: CGPoint(x: columnX[2], y: topY),
            .r: CGPoint(x: columnX[2], y: bottomY),

            .n: CGPoint(x: columnX[1], y: middleY)
        ]
    }

    var body: some View {
        ZStack {

            // 縦ライン
            ForEach(columnX, id: \.self) { x in
                Path { path in
                    path.move(to: CGPoint(x: x, y: topY))
                    path.addLine(to: CGPoint(x: x, y: bottomY))
                }
                .stroke(Color.white.opacity(0.5), lineWidth: 3)
            }

            // ニュートラル横ライン
            Path { path in
                path.move(to: CGPoint(x: columnX[0], y: middleY))
                path.addLine(to: CGPoint(x: columnX[2], y: middleY))
            }
            .stroke(Color.white.opacity(0.5), lineWidth: 3)

            // ノブ
            Circle()
                .fill(Color.gray)
                .frame(width: 30, height: 30)
                .position(knobPosition)
                .gesture(
                    DragGesture()
                        .onChanged { value in
                            updateKnob(with: value.location)
                        }
                        .onEnded { _ in
                            snapToNearest()
                        }
                )
        }
        .onAppear {
            knobPosition = positions[currentGear] ?? positions[.n]!
        }
    }

    func updateKnob(with location: CGPoint) {

        let nearestColumn = columnX.min(by: {
            abs(location.x - $0) < abs(location.x - $1)
        }) ?? columnX[1]

        var newY = location.y
        newY = min(max(newY, topY), bottomY)

        if abs(location.y - middleY) < 20 {
            knobPosition = CGPoint(
                x: location.x.clamped(to: columnX[0]...columnX[2]),
                y: middleY
            )
        } else {
            knobPosition = CGPoint(x: nearestColumn, y: newY)
        }
    }

    func snapToNearest() {
        guard let nearest = positions.min(by: {
            distance(knobPosition, $0.value) <
            distance(knobPosition, $1.value)
        }) else { return }

        withAnimation(.spring(response: 0.25, dampingFraction: 0.7)) {
            knobPosition = nearest.value
            currentGear = nearest.key
        }
    }

    func distance(_ a: CGPoint, _ b: CGPoint) -> CGFloat {
        sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))
    }
}

////////////////////////////////////////////////////////////
// CGFloat clamp
////////////////////////////////////////////////////////////

extension CGFloat {
    func clamped(to range: ClosedRange<CGFloat>) -> CGFloat {
        Swift.min(Swift.max(self, range.lowerBound), range.upperBound)
    }
}
////////////////////////////////////////////////////////////
// ペダル
////////////////////////////////////////////////////////////

struct PedalView: View {

    let title: String
    @Binding var value: CGFloat

    var body: some View {
        VStack(spacing: 8) {

            Text(title)
                .foregroundStyle(.white.opacity(0.8))

            CustomVerticalSlider(value: $value)
                .frame(width: 40, height: 140)

            Text(String(format: "%.0f %%", value * 100))
                .foregroundStyle(.white.opacity(0.7))
                .font(.caption)
        }
    }
}

////////////////////////////////////////////////////////////
// 縦スライダー
////////////////////////////////////////////////////////////

struct CustomVerticalSlider: View {

    @Binding var value: CGFloat
    @State private var lastValue: CGFloat = 0

    var body: some View {
        GeometryReader { geo in
            ZStack(alignment: .bottom) {

                Capsule()
                    .fill(Color.white.opacity(0.15))
                    .frame(width: 6)

                Capsule()
                    .fill(Color.white.opacity(0.8))
                    .frame(width: 6,
                           height: geo.size.height * value)

                Circle()
                    .fill(Color.white)
                    .frame(width: 28, height: 28)
                    .offset(y: -geo.size.height * value + 14)
                    .gesture(
                        DragGesture()
                            .onChanged { gesture in
                                let delta = -gesture.translation.height / geo.size.height
                                let newValue = lastValue + delta
                                value = min(max(newValue, 0), 1)
                            }
                            .onEnded { _ in
                                lastValue = value
                            }
                    )
            }
        }
    }
}

#Preview(traits: .landscapeRight) {
    ContentView()
}
