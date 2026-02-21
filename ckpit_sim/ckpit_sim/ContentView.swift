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

    var dummySpeed: CGFloat {
        sliderValue * 1.12 * 100
    }

    var dummyRPM: CGFloat {
        (sliderValue * 100) * 200
    }

    var body: some View {
        GeometryReader { geo in
            HStack(spacing: 0) {

                // ===== 左85% =====
                ZStack {

                    Color(red: 0.08, green: 0.12, blue: 0.20)

                    VStack {
                        HStack(alignment: .firstTextBaseline) {

                            // ===== スピード =====
                            HStack(alignment: .firstTextBaseline, spacing: 8) {
                                Text("\(Int(dummySpeed))")
                                    .font(.system(size: 80, weight: .bold))
                                    .monospacedDigit()
                                    .foregroundStyle(.green)
                                    .lineLimit(1)

                                Text("km/h")
                                    .font(.system(size: 28, weight: .medium))
                                    .foregroundStyle(.green.opacity(0.8))
                            }

                            Spacer()

                            // ===== RPM =====
                            HStack(alignment: .firstTextBaseline, spacing: 8) {
                                Text("\(Int(dummyRPM))")
                                    .font(.system(size: 80, weight: .bold))
                                    .monospacedDigit()
                                    .foregroundStyle(.orange)
                                    .lineLimit(1)
                                    .minimumScaleFactor(0.6)
                                    .layoutPriority(1)

                                Text("RPM")
                                    .font(.system(size: 28, weight: .medium))
                                    .foregroundStyle(.orange.opacity(0.8))
                            }
                        }
                        .padding(.horizontal, 60)
                        .padding(.top, 40)

                        Spacer()
                    }

                    // ===== シフト + ギア表示 =====
                    HStack(spacing: 30) {

                        ShiftView(currentGear: $currentGear)
                            .frame(width: 220, height: 260)

                        Text(currentGear.rawValue)
                            .font(.system(size: 110, weight: .bold))
                            .foregroundStyle(.yellow)
                            .shadow(radius: 10)

                    }
                    .offset(x: -160, y: 120)

                    // ===== ペダル =====
                    VStack {
                        Spacer()
                        HStack {
                            Spacer()

                            HStack(spacing: 70) {
                                PedalView(title: "CL", value: $clutchValue)
                                PedalView(title: "BR", value: $brakeValue)
                            }
                            .padding(.trailing, 120)
                            .padding(.bottom, 40)
                        }
                    }
                }
                .frame(width: geo.size.width * 0.80)

                // ===== 右15% =====
                ZStack {
                    Color(red: 0.18, green: 0.18, blue: 0.20)

                    CustomVerticalSlider(
                        value: $sliderValue,
                        knobSize: 66,      // ← 大きく
                        trackWidth: 5,     // ← 太く
                        trackHeightRatio: 0.6   // ← 60%の長さに
                    )
                    .frame(width: 80)      // ← スライダー自体も少し広げる
                    .padding(.vertical, 60)
                }
                .frame(width: geo.size.width * 0.20)
            }
        }
        .ignoresSafeArea()
    }
}

////////////////////////////////////////////////////////////
// 改良版 Hパターン シフト
////////////////////////////////////////////////////////////

struct ShiftView: View {

    @Binding var currentGear: Gear
    @State private var knobPosition: CGPoint = .zero

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

            ForEach(columnX, id: \.self) { x in
                Path { path in
                    path.move(to: CGPoint(x: x, y: topY))
                    path.addLine(to: CGPoint(x: x, y: bottomY))
                }
                .stroke(Color.white.opacity(0.5), lineWidth: 3)
            }

            Path { path in
                path.move(to: CGPoint(x: columnX[0], y: middleY))
                path.addLine(to: CGPoint(x: columnX[2], y: middleY))
            }
            .stroke(Color.white.opacity(0.5), lineWidth: 3)

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
        var newY = location.y
        newY = min(max(newY, topY), bottomY)
        let isInNeutralZone = abs(newY - middleY) < 25

        if isInNeutralZone {
            let clampedX = location.x.clamped(to: columnX[0]...columnX[2])
            knobPosition = CGPoint(x: clampedX, y: middleY)
        } else {
            let currentColumn = columnX.min(by: {
                abs(knobPosition.x - $0) < abs(knobPosition.x - $1)
            }) ?? columnX[1]
            knobPosition = CGPoint(x: currentColumn, y: newY)
        }
    }

    func snapToNearest() {
        if abs(knobPosition.y - middleY) < 1 {
            withAnimation(.spring()) {
                knobPosition.y = middleY
                currentGear = .n
            }
            return
        }

        guard let nearest = positions
            .filter({ $0.key != .n })
            .min(by: {
                distance(knobPosition, $0.value) <
                distance(knobPosition, $1.value)
            }) else { return }

        withAnimation(.spring()) {
            knobPosition = nearest.value
            currentGear = nearest.key
        }
    }

    func distance(_ a: CGPoint, _ b: CGPoint) -> CGFloat {
        sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))
    }
}

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

            Text("\(Int(value * 100)) %")
                .foregroundStyle(.white.opacity(0.7))
                .font(.caption)
                .animation(.easeOut(duration: 0.35), value: value)
        }
    }
}

////////////////////////////////////////////////////////////
// 縦スライダー
////////////////////////////////////////////////////////////

struct CustomVerticalSlider: View {
    @State private var returnTimer: Timer?
    @Binding var value: CGFloat
    @State private var previousDragValue: CGFloat = 0

    var knobSize: CGFloat = 28      // ← 追加
    var trackWidth: CGFloat = 6     // ← 追加
    var trackHeightRatio: CGFloat = 0.5   // ← 追加（1.0 = 100%）

    var body: some View {
        GeometryReader { geo in

            let trackHeight = geo.size.height * trackHeightRatio
            let verticalOffset = (geo.size.height - trackHeight) / 2

            ZStack {

                // 背景トラック
                Capsule()
                    .fill(Color.white.opacity(0.15))
                    .frame(width: trackWidth, height: trackHeight)
                    .position(
                        x: geo.size.width / 2,
                        y: geo.size.height / 2
                    )

                // アクティブ部分
                Capsule()
                    .fill(Color.white.opacity(0.8))
                    .frame(width: trackWidth,
                           height: trackHeight * value)
                    .position(
                        x: geo.size.width / 2,
                        y: geo.size.height - verticalOffset - (trackHeight * value / 2)
                    )

                // ノブ
                Circle()
                    .fill(Color.white)
                    .frame(width: knobSize, height: knobSize)
                    .position(
                        x: geo.size.width / 2,
                        y: geo.size.height - verticalOffset - trackHeight * value
                    )
                    .gesture(
                        DragGesture()
                            .onChanged { gesture in
                                let delta = -gesture.translation.height / trackHeight
                                let change = delta - previousDragValue
                                previousDragValue = delta

                                value += change
                                value = min(max(value, 0), 1)
                            }
                            .onEnded { _ in
                                previousDragValue = 0
                                returnTimer?.invalidate()

                                returnTimer = Timer.scheduledTimer(withTimeInterval: 0.016, repeats: true) { timer in
                                    if value > 0 {
                                        value -= 0.03
                                        value = max(value, 0)
                                    } else {
                                        timer.invalidate()
                                    }
                                }
                            }
                    )
            }
        }
    }
}

#Preview(traits: .landscapeRight) {
    ContentView()
}
