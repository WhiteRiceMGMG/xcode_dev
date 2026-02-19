import SwiftUI

struct ContentView: View {
    
    var body: some View {
        ZStack {
            Color(.systemGray6)
                .ignoresSafeArea()
            
            HStack(spacing: 50) {
                
                // ===== 左：メーター群 =====
                HStack(spacing: 60) {
                    GaugeView(title: "RPM")
                    GaugeView(title: "SPEED")
                }
                
                // ===== 中央：ボタン群 =====
                VStack(spacing: 30) {
                    
                    HStack(spacing: 30) {
                        ControlButton(title: "GEAR")
                        ControlButton(title: "ENGINE")
                    }
                    
                    HStack(spacing: 30) {
                        PedalButton(title: "ACCEL", color: .blue)
                        PedalButton(title: "BRAKE", color: .red)
                    }
                }
                
                // ===== 右：縦アクセルバー =====
                VStack(spacing: 20) {
                    Text("ACCEL MAX")
                        .font(.caption)
                    
                    ZStack(alignment: .bottom) {
                        Capsule()
                            .frame(width: 40, height: 200)
                            .foregroundColor(.gray.opacity(0.3))
                        
                        Capsule()
                            .frame(width: 40, height: 100)
                            .foregroundColor(.blue)
                    }
                }
            }
            .padding()
        }
    }
}


// =======================
// メーター
// =======================

struct GaugeView: View {
    
    var title: String
    
    var body: some View {
        ZStack {
            
            Circle()
                .trim(from: 0.5, to: 1)
                .stroke(lineWidth: 12)
                .frame(width: 200, height: 200)
                .rotationEffect(.degrees(180))
            
            Rectangle()
                .frame(width: 4, height: 80)
                .offset(y: -40)
                .rotationEffect(.degrees(-30))
            
            VStack {
                Spacer()
                Text(title)
                    .font(.headline)
            }
        }
    }
}


// =======================
// 小ボタン
// =======================

struct ControlButton: View {
    var title: String
    
    var body: some View {
        Button(action: {
            // 空アクション
        }) {
            Text(title)
                .frame(width: 120, height: 60)
                .background(Color.gray.opacity(0.3))
                .cornerRadius(10)
        }
    }
}


// =======================
// ペダルボタン
// =======================

struct PedalButton: View {
    var title: String
    var color: Color
    
    var body: some View {
        Button(action: {
            // 空アクション
        }) {
            Text(title)
                .frame(width: 120, height: 120)
                .background(color.opacity(0.4))
                .cornerRadius(12)
        }
    }
}


#Preview {
    ContentView()
}

